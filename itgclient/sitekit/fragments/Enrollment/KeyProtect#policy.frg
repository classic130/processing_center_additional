<!-- VSSKBEGINPOLICYVAL#policy#1 -->
<!-- VSSKENDPOLICYVAL#policy#1 -->


<!-- VSSKBEGINPOLICYVAL#policy#2 -->
       if %%bProtect%% then
           keyflags = keyflags OR 2
       end if 
<!-- VSSKENDPOLICYVAL#policy#2 -->


<!-- VSSKBEGINPOLICYVAL#policy#3 -->       
if (%%bProtect%%)
{
      KeyFlags = KeyFlags | 2;
}
<!-- VSSKENDPOLICYVAL#policy#3 -->


<!-- VSSKBEGINPOLICYVAL#policy#4 -->       
    if %%bProtect%% then
       	Import.KeyUserProtected = true
    else
       	Import.KeyUserProtected = false
    end if
<!-- VSSKENDPOLICYVAL#policy#4 -->


<!-- VSSKBEGINPOLICYVAL#policy#5 -->       
<!-- VSSKENDPOLICYVAL#policy#5 -->


<!-- VSSKBEGINPOLICYVAL#policy#6 -->       
<!-- VSSKENDPOLICYVAL#policy#6 -->

<!-- VSSKBEGINPOLICYVAL#policy#7 -->       
<!-- VSSKENDPOLICYVAL#policy#7 -->