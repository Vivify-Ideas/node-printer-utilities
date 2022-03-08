{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "betshop_printer",
      "sources": [ "./src/betshop_printer.cpp" ],
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
          'cflags':[
            '<!(cups-config --cflags)'
          ],
          'ldflags':[
            '<!(cups-config --libs)'
          ],
          'libraries':[
            '<!(cups-config --libs)'
          ],
          'link_settings': {
            'libraries': [
              '<!(cups-config --libs)',
              '-ludev'
            ]
          }
        }]
      ]
    }
  ]
}