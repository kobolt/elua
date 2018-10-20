-- Gadget Renesas GR-SAKURA eLua image build configuration

return {
  cpu = 'RX63N',
  components = {
    sercon = { uart = 0, speed = 9600, timer = 0 },
    romfs = true,
    shell = true,
  },
  modules = {
    generic = { 'pio', 'tmr', 'pd', 'uart', 'pack', 'bit', 'elua', 'cpu', 'all_lua' }

  }
}

