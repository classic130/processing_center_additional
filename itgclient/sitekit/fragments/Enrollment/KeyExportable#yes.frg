<!-- VSSKBEGINPOLICYVAL#yes#1 -->
          keyflags = keyflags OR 1
<!-- VSSKENDPOLICYVAL#yes#1 -->

<!-- VSSKBEGINPOLICYVAL#yes#2 -->
          KeyFlags = KeyFlags | 1;
<!-- VSSKENDPOLICYVAL#yes#2 -->

<!-- VSSKBEGINPOLICYVAL#yes#3 -->
          KeyFlags = KeyFlags OR 0
<!-- VSSKENDPOLICYVAL#yes#3 -->

<!-- VSSKBEGINPOLICYVAL#yes#4 -->
          KeyFlags = KeyFlags | 0;
<!-- VSSKENDPOLICYVAL#yes#4 -->

<!-- VSSKBEGINPOLICYVAL#yes#5 -->
     <!-- Set the KeyExportable flag to 1 in case if the key is exportable -->
     <SCRIPT LANGUAGE=JavaScript>
     IVSPTA.IsPrivateKeyExportable = 1
     </SCRIPT>
<!-- VSSKENDPOLICYVAL#yes#5 -->

