<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                    <option value=""> </option>
                <?php foreach($shares as $share): ?>
                    <option><?= $share["symbol"] ?></option>
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
<div>
    <a href="javascript:history.go(-1);">Back</a>
</div>
