<?php

    // configuration
    require("../includes/config.php"); 
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //validate submission
        if (empty($_POST["cash"]))
        {
            apologize("You must provide a cash.");
        }
        else if(!preg_match("/^\d+$/", $_POST["cash"]))
        {
            apologize("Wrong cash.");
        }
        else
        {
            query("UPDATE users SET cash = cash + ? WHERE id = ?",  $_POST["cash"], $_SESSION["id"]);
            redirect("/");
        } 
    }
    else
    {// render portfolio
        render("add_cash_form.php", ["title" => "Add cash"]);
    }
?>
