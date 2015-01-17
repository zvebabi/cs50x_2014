<?php

    // configuration
    require("../includes/config.php"); 
    
    //take a table from SQL
    $rows = query("SELECT * FROM cart WHERE id = ?", $_SESSION["id"]);
    //take info about  cash
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    //set table in portfolio
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
                ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash[0]["cash"], "title" => "Portfolio"]);

?>
