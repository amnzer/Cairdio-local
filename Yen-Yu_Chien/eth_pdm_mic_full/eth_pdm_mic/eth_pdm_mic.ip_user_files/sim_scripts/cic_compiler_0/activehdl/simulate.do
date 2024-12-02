transcript off
onbreak {quit -force}
onerror {quit -force}
transcript on

asim +access +r +m+cic_compiler_0  -L xpm -L xbip_utils_v3_0_10 -L axi_utils_v2_0_6 -L cic_compiler_v4_0_16 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.cic_compiler_0 xil_defaultlib.glbl

do {cic_compiler_0.udo}

run 1000ns

endsim

quit -force
