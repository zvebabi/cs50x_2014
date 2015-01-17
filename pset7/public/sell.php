<?php

    // configuration
    require("../includes/config.php"); 
    
    //take a table from SQL
    $shares = query("SELECT * FROM cart WHERE id = ?", $_SESSION["id"]);
    //take info about  cash
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    //sell or render sell_form
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
         // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must choose a symbol.");
        }
        else
        {
            //check current share's price
            $stock = lookup($_POST["symbol"]);
            if ($stock !== false)
            {
                //remembe shares value
                $share_count = query("SELECT shares FROM cart WHERE id = ? AND symbol= ?", $_SESSION["id"], $_POST["symbol"]);
                //delete shares from DB
                query("DELETE FROM cart WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
                //update cash
                $cost = $share_count[0]["shares"]*$stock["price"];
                query("UPDATE users SET cash = cash + ? WHERE id = ?", $cost, $_SESSION["id"]);
                query("INSERT INTO history(id, transaction, date, symbol, shares, price) VALUES (?,'SELL', CURRENT_TIMESTAMP, ?, ?,?)",$_SESSION["id"], $_POST["symbol"], $share_count[0]["shares"], $cost);
            }
            else
            {
                apologize("Wrong symbol!");
            }     
        }
        redirect("/");
    }
    else
    {
        // render portfolio
        render("sell_form.php", ["shares" => $shares, "title" => "Sell"]);
    }
?>
