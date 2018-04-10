
vsctlps.dll: dlldata.obj vsctl_p.obj vsctl_i.obj
	link /dll /out:vsctlps.dll /def:vsctlps.def /entry:DllMain dlldata.obj vsctl_p.obj vsctl_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del vsctlps.dll
	@del vsctlps.lib
	@del vsctlps.exp
	@del dlldata.obj
	@del vsctl_p.obj
	@del vsctl_i.obj
