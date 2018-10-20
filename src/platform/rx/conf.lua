-- Configuration file for the RX backend

specific_files = "sakura_crt0.S platform.c uart.c timer.c pio.c"
local ldscript = "sakura_rx.ld"

-- Prepend with path
specific_files = utils.prepend_path( specific_files, sf( "src/platform/%s", platform ) )
ldscript = sf( "src/platform/%s/%s", platform, ldscript )

addm{ "FOR" .. comp.cpu:upper(), 'gcc' }

-- Standard GCC flags
addcf{ '-ffunction-sections', '-fdata-sections', '-mcpu=rx600', '-Wall', '-Wextra' }
addlf{ '-nostartfiles', '-T', ldscript, '-Wl,--gc-sections', }
addaf{ '-x', 'assembler-with-cpp', '-Wall' }
addlib{ 'c','gcc','m' }

-- Toolset data
tools.rx = {}

-- Array of file names that will be checked against the 'prog' target; their absence will force a rebuild
tools.rx.prog_flist = { output .. ".bin" }

-- We use 'gcc' as the assembler
toolset.asm = toolset.compile

