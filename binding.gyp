{
  "variables": {
    "openssl_fips" : "0" 
  },
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "betshop_printer",
      "sources": [ "./src/betshop_printer.cpp" ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'cflags_cc+': [
        "-Wunused-result",
      ],
      'conditions': [
        ['OS!="win"', {
          "defines": [
            "_HAS_EXCEPTIONS=1"
          ],
          'cflags':[
            '<!(cups-config --cflags)'
          ],
          'ldflags':[
            '<!(cups-config --libs)'
          ],
          'libraries':[
            '<!(cups-config --libs)',
          ],
          'link_settings': {
            'libraries': [
              '<!(cups-config --libs)',
            ]
          }
        }],
        ['OS=="linux"', {
          'link_settings': {
            'libraries': [
              '/usr/local/lib/libwkhtmltox.so.0'
            ],
          }
        }]
      ]
    }
  ]
}