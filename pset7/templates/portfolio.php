<ul class="nav nav-tabs">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li class="dropdown">
         <a class="dropdown-toggle"
       data-toggle="dropdown"
       href="#">
        My Account
        <b class="caret"></b>
      </a>
    <ul class="dropdown-menu">
      <a href="change_passwd.php">Change password</a>
      </br>
      <a href="add_cash.php">Add cash</a>
    </ul>
    </li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>


<table class="table table-striped">
  <thead>
    <tr>
    <th>Symbol</th>
    <th>Name</th>
    <th>Shares</th>
    <th>Price</th>
    <th>TOTAL</th>
    </tr>
  </thead>    
  <tbody> 
    <?php foreach ($positions as $position): ?>
    <tr>
        <td class="text-left"><?= $position["symbol"] ?></td>
        <td class="text-left"><?= $position["name"]   ?></td>
        <td class="text-left"><?= $position["shares"] ?></td>
        <td class="text-left">$<?= $position["price"] ?></td>
        <td class="text-left">$<?= number_format($position["shares"]*$position["price"],2,'.',',') ?></td>
    </tr>
    <?php endforeach ?>
    <tr>
        <td></td>
        <td></td>
        <td></td>
        <td class="text-left"><strong>CASH<strong></td>
        <td class="text-left">$<?= number_format($cash,2,'.',',') ?></td>
    </tr>
  </tbody>

    
</table>
