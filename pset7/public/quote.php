<?php

    // configuration
    require("../includes/config.php"); 
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            $message = sprintf("A share of %s (%s) costs $%s", $stock["name"], $stock["symbol"], number_format($stock["price"],2,'.',''));
            render("quote_answer.php", ["message" => $message]);
        } 
    }
    else
    {// render portfolio
        render("quote_form.php", ["title" => "Quote"]);
    }
?>
