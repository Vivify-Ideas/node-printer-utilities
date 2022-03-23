{
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
        "-Wcast-function-type"
      ],
      'conditions': [
        ['OS!="linux"', {'sources/': [['exclude', '_linux\\.cc$']]}],
        ['OS!="mac"', {'sources/': [['exclude', '_mac\\.cc|mm?$']]}],
        ['OS!="win"', {
          'sources/': [['exclude', '_win\\.cc$']]}, {
          'sources/': [['exclude', '_posix\\.cc$']]
        }],
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
              '-ludev',
              '/usr/local/lib/libwkhtmltox.so.0'
            ]
          }
        }]
      ]
    }
  ]
}