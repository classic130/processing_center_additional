
Ptav3ps.dll: dlldata.obj Ptav3_p.obj Ptav3_i.obj
	link /dll /out:Ptav3ps.dll /def:Ptav3ps.def /entry:DllMain dlldata.obj Ptav3_p.obj Ptav3_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Ptav3ps.dll
	@del Ptav3ps.lib
	@del Ptav3ps.exp
	@del dlldata.obj
	@del Ptav3_p.obj
	@del Ptav3_i.obj
