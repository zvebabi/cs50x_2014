<?php

    // configuration
    require("../includes/config.php"); 
        // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["old_passwd"]))
        {
            apologize("You must provide your current password.");
        }
        else if (empty($_POST["new_passwd"]))
        {
            apologize("You must provide your new password.");
        }
        // query database for user's hash
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);

        // compare hash of user's input current_passw against hash that's in database
        if (crypt($_POST["old_passwd"], $rows[0]["hash"]) == $rows[0]["hash"])
        {
            query("UPDATE users SET hash = ? WHERE id = ?",crypt($_POST["new_passwd"]) ,$_SESSION["id"]);
            // redirect to portfolio
            $message = sprintf("Your password has been changed!");
            render("change_passwd_form_ok.php", ["message" => $message]);
        }
        else
        {    
            // else apologize
            apologize("Invalid current password.");
        }
    }
    else
    {       
        // render form
        render("change_passwd_form.php", ["title" => "Change Password"]);
    }
?>
