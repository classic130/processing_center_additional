
VGSEps.dll: dlldata.obj VGSE_p.obj VGSE_i.obj
	link /dll /out:VGSEps.dll /def:VGSEps.def /entry:DllMain dlldata.obj VGSE_p.obj VGSE_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VGSEps.dll
	@del VGSEps.lib
	@del VGSEps.exp
	@del dlldata.obj
	@del VGSE_p.obj
	@del VGSE_i.obj
