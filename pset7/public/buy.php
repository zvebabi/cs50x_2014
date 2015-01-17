<?php

    // configuration
    require("../includes/config.php"); 

    //sell or render sell_form
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
         // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        else if(empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
        else if(!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Wrong shares.");
        }
        else
        {
            //check current share's price
            $stock = lookup($_POST["symbol"]);
            if ($stock !== false)
            {
                //remembe shares value
                $cash = query("SELECT cash FROM users WHERE id = ? ", $_SESSION["id"]);
                //if not-enough money
                if($cash[0]["cash"] < $_POST["shares"]*$stock["price"])
                {
                    apologize("You can't afford that.");
                }
                //updating DB
                else
                {   
                    //create shares in cart
                    $query = query("INSERT INTO cart(id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($stock["symbol"]), $_POST["shares"]);
                    if ($query === false)
                    {
                       apologize("Error while buying shares.");
                    }
                    $cost = $_POST["shares"]*$stock["price"];
                    //update cash
                    query("UPDATE users SET cash = cash - ? WHERE id = ?",  $cost, $_SESSION["id"]);
                    query("INSERT INTO history(id, transaction, date, symbol, shares, price) VALUES (?,'BUY', CURRENT_TIMESTAMP, ?, ?, ?)",$_SESSION["id"], $_POST["symbol"], $_POST["shares"], $cost);
                }
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
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
