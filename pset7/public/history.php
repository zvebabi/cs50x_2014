<?php

    // configuration
    require("../includes/config.php"); 
    
    //take a table from SQL
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    //set table in history
    $positions = [];
    foreach ($rows as $row)
    {
        $positions[] = [
            "transaction" => $row["transaction"],
            "date" => $row["date"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"]
            ];
    }
    
    // render portfolio
    render("history_form.php", ["positions" => $positions, "title" => "History"]);

?>
