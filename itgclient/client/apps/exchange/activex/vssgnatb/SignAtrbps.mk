
SignAtrbps.dll: dlldata.obj SignAtrb_p.obj SignAtrb_i.obj
	link /dll /out:SignAtrbps.dll /def:SignAtrbps.def /entry:DllMain dlldata.obj SignAtrb_p.obj SignAtrb_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SignAtrbps.dll
	@del SignAtrbps.lib
	@del SignAtrbps.exp
	@del dlldata.obj
	@del SignAtrb_p.obj
	@del SignAtrb_i.obj
