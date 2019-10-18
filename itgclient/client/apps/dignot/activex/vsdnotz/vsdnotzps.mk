
vsdnotzps.dll: dlldata.obj vsdnotz_p.obj vsdnotz_i.obj
	link /dll /out:vsdnotzps.dll /def:vsdnotzps.def /entry:DllMain dlldata.obj vsdnotz_p.obj vsdnotz_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del vsdnotzps.dll
	@del vsdnotzps.lib
	@del vsdnotzps.exp
	@del dlldata.obj
	@del vsdnotz_p.obj
	@del vsdnotz_i.obj
