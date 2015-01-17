<form action="change_passwd.php" method="post">
    <fieldset>
        <div class="form-group">
            <input id="o_pass" autofocus class="form-control" name="old_passwd" placeholder="Current password" type="password"/>
            <input onchange="if ($('#o_pass').get(0).type=='password') $('#o_pass').get(0).type='text'; else $('#o_pass').get(0).type='password';" name="fff" type="checkbox" value="false">Show
        </div>
        <div class="form-group">
            <input id="n_pass" class="form-control" name="new_passwd" placeholder="New password" type="password"/>
            <input onchange="if ($('#n_pass').get(0).type=='password') $('#n_pass').get(0).type='text'; else $('#n_pass').get(0).type='password';" name="fff" type="checkbox" value="false">Show
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Change Password</button>
              &nbsp&nbsp or &nbsp <a href="javascript:history.go(-1);">Previous page</a>
        </div>
        
    </fieldset>
</form>

