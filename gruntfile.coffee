module.exports = (grunt) ->
  grunt.initConfig
    pkg: grunt.file.readJSON("package.json")

    notify:
      regarde:
        options:
          title: 'Grunt'
          message: 'Snipers on the roof, sir!'
      coffee:
        options:
          title: 'Grunt'
          message: 'Would you take some sugar with that coffee ?'
      less:
        options:
          title: 'Grunt'
          message: 'LESS is more. Mission accomplished.'
      compile:
        options:
          title: 'Grunt'
          message: 'Compiling. Mission accomplished, sir.'
      warning:
        options:
          title: 'Grunt Error !!'
          message: 'Seems that you loose some code skills... Cannot compile this thing !'

    coffee:
      compile:
        options:
          bare: true
        files: [
            expand: true
            cwd: 'Common/Bin/Data/coffee/'
            src: ['**/*.coffee']
            dest: 'Common/Bin/Data/js/'
            rename: (dest, src) ->
              dest + src.replace '.coffee', '.js'
        ]

    regarde:
      coffee:
        files: 'Common/Bin/Data/coffee/**/*.coffee'
        tasks: ['coffee:compile','notify:coffee']
        spawn: false

  grunt.loadNpmTasks 'grunt-contrib-coffee'
  grunt.loadNpmTasks 'grunt-notify'
  grunt.loadNpmTasks 'grunt-regarde'

  grunt.registerTask 'compile', ['notify:compile','coffee:compile']
  grunt.registerTask 'watch', ['notify:regarde','regarde']
  grunt.registerTask 'default', ['compile','watch']