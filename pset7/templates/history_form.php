<table class="table table-striped">
  <thead>
    <tr>
    <th>Transaction</th>
    <th>Date/Time</th>
    <th>Symbol</th>
    <th>Shares</th>
    <th>Price</th>
    </tr>
  </thead>    
  <tbody> 
    <?php foreach ($positions as $position): ?>
    <tr>
        <td class="text-left"><?= $position["transaction"] ?></td>
        <td class="text-left"><?= date("Ymd H:i",strtotime($position["date"]))   ?></td>
        <td class="text-left"><?= $position["symbol"]   ?></td>
        <td class="text-left"><?= $position["shares"] ?></td>
        <td class="text-left">$<?= number_format($position["price"], 2, '.', ',') ?></td>
    </tr>
    <?php endforeach ?>
  </tbody>
</table>
