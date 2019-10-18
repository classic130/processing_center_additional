
ConfigChkps.dll: dlldata.obj ConfigChk_p.obj ConfigChk_i.obj
	link /dll /out:ConfigChkps.dll /def:ConfigChkps.def /entry:DllMain dlldata.obj ConfigChk_p.obj ConfigChk_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ConfigChkps.dll
	@del ConfigChkps.lib
	@del ConfigChkps.exp
	@del dlldata.obj
	@del ConfigChk_p.obj
	@del ConfigChk_i.obj
