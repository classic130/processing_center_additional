
VSSCps.dll: dlldata.obj VSSC_p.obj VSSC_i.obj
	link /dll /out:VSSCps.dll /def:VSSCps.def /entry:DllMain dlldata.obj VSSC_p.obj VSSC_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VSSCps.dll
	@del VSSCps.lib
	@del VSSCps.exp
	@del dlldata.obj
	@del VSSC_p.obj
	@del VSSC_i.obj
