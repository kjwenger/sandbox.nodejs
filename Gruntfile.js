/*global module*/
/*jslint node:true */
/*jshint strict:true */

module.exports = function (grunt) {
    "use strict";
    var path = require('path'),
        toffee_script = 'node_modules/toffee-script/bin/coffee',
        dbpath = path.join(process.cwd(), 'test', 'databases', '2.0');
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        yeoman: {
            databases: {
                dbpath: dbpath
            }
        },
        clean: {
            build: [
                'src/main/build',
                'target/build'
            ],
            test_databases: [
                '<%= yeoman.databases.dbpath %>'
            ]
        },
        mkdir: {
            build: {
                options: {
                    create: [
                        'target/build'
                    ]
                }
            },
            test_databases: {
                options: {
                    create: [
                        '<%= yeoman.databases.dbpath %>'
                    ]
                }
            }
        },
        symlink: {
            options: {
                overwrite: true
            },
            build: {
                src: 'target/build',
                dest: 'src/main/build'
            }
        },
        command: {
            mongo_start: {
                cmd: 'bbs mongo start 2.0.49 --auth --port 25000 --dbpath ' + dbpath
            },
            mongo_stop: {
                cmd: 'bbs mongo stop 2.0.49'
            }
        },
        toffee: {
            options: {
                bare: true,
                join: false,
                sourceMap: true
            },
            'target/app/constants.js':  'src/main/toffee/constants.toffee',
            'target/app/utils.js': 'src/main/toffee/utils.toffee',
            'target/app/model/location.js': 'src/main/toffee/model/location.toffee',
            'target/app/model/address.js': 'src/main/toffee/model/address.toffee',
            'target/test/features/location-steps.js': 'src/test/features/location-steps.toffee',
            'target/test/features/topic-steps.js': 'src/test/features/topic-steps.toffee',
            'target/test/features/species-steps.js': 'src/test/features/species-steps.toffee',
            'target/test/specs/location-spec.js': 'src/test/specs/location-spec.toffee',
            'target/test/mocha/location-test.js': 'src/test/mocha/location-test.toffee'
        },
        easy_mongo_fixture: {
            load: {
                options: {
                    host: '127.0.0.1',
                    port: 27017,
                    username: 'sa',
                    password: '',
                    database: 'test',
                    dir: 'src/test/fixtures',
                    override: true
                },
                collections: [
                    'locations'
                ],
                action: 'load'
            },
            save: {
                options: {
                    host: '127.0.0.1',
                    port: 27017,
                    username: 'sa',
                    password: '',
                    database: 'test',
                    dir: 'src/test/fixtures',
                    override: true
                },
                collections: [
                    'locations'
                ],
                action: 'save'
            }
        },
        execute: {
            clean_addon: {
                options: {
                    cwd: 'src/main',
                    args: [
                        'clean'
                    ]
                },
                src: [
                    'node_modules/node-gyp/bin/node-gyp.js'
                ]
            },
            configure_addon: {
                options: {
                    cwd: 'src/main',
                    args: [
                        'configure'
                    ]
                },
                src: [
                    'node_modules/node-gyp/bin/node-gyp.js'
                ]
            },
            build_addon: {
                options: {
                    cwd: 'src/main',
                    args: [
                        'build'
                    ]
                },
                src: [
                    'node_modules/node-gyp/bin/node-gyp.js'
                ]
            }
        },
        gyp: {
            addon: {}
        },
        eslint: {
            options: {
                silent: false
            },
            src: [
                'target/app/**/*.js'
            ]
        },
        jshint: {
            all: [
                'target/app/**/*.js'
            ],
            options: {
                jshintrc: true
            }
        },
        jsduck: {
            main: {
                src: [
                    'target/app/**/*.js'
                ],
                dest: 'target/doc',
                options: {
                    'builtin-classes': true,
                    warnings: [
                        '-no_doc',
                        '-dup_member',
                        '-link_ambiguous'
                    ],
                    tags: [
                        'src/main/rb/tag/addon_tag.rb',
                        'src/main/rb/tag/author_tag.rb',
                        'src/main/rb/tag/date_tag.rb',
                        'src/main/rb/tag/example_tag.rb',
                        'src/main/rb/tag/module_tag.rb',
                        'src/main/rb/tag/see_tag.rb'
                    ]
                }
            }
        },
        mongodb_fixtures: {
            options: {
                // Task-specific options go here.
            },
            your_target: {
                // Target-specific file lists and/or options go here.
            }
        },
        env: {
            lib: {
                LD_LIBRARY_PATH: '../sandbox.cpp/build'
            },
            debug: {
                DEBUG: 'species-steps'
            }
        },
        cucumberjs: {
            options: {
                steps: "target/test/features/",
                format: 'pretty',
                output: 'target/test/features/report.html',
                formatHtml: 'html',
                saveJson: true,
                theme: 'bootstrap',
                debug: false
            },
            features: [
                'src/test/features/location.feature',
                'src/test/features/topic.feature',
                'src/test/features/species.feature'
            ]
        },
        jasmine_node: {
            options: {
                specNameMatcher: 'spec',
                forceExit: true,
                verbose: true
            },
            test: [
                'target/test/specs/'
            ]
        },
        mochaTest: {
            test: {
                options: {
                    reporter: 'spec',
                    captureFile: 'target/test/mocha/results.txt',
                    quiet: false,
                    clearRequireCache: false
                },
                src: ['target/test/mocha/**/*.js']
            }
        }
    });
    grunt.loadNpmTasks('grunt-contrib-clean');
    grunt.loadNpmTasks('grunt-contrib-coffee');
    grunt.loadNpmTasks('grunt-toffee');
    grunt.loadNpmTasks('grunt-contrib-jshint');
    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-commands');
    grunt.loadNpmTasks('grunt-easy-mongo-fixture');
    grunt.loadNpmTasks('grunt-contrib-symlink');
    grunt.loadNpmTasks('grunt-node-gyp');
    grunt.loadNpmTasks('grunt-execute');
    grunt.loadNpmTasks('grunt-env');
    grunt.loadNpmTasks('grunt-cucumberjs');
    grunt.loadNpmTasks('grunt-jasmine-node');
    grunt.loadNpmTasks('grunt-mocha-test');
    grunt.loadNpmTasks('grunt-jsduck');
    grunt.loadNpmTasks('grunt-mkdir');
    grunt.loadNpmTasks('gruntify-eslint');
    grunt.registerTask('test:mongo', [
        // stop open MongoDB instances, could happen if a test stops due an exception
        'command:mongo_stop',
        'clean:test_databases',
        'mkdir:test_databases',
        'command:mongo_start',
        'jasmine_node:test',
        'command:mongo_stop'
    ]);
    grunt.registerTask('fixtures:load', [
        'easy_mongo_fixture:load'
    ]);
    grunt.registerTask('fixtures:save', [
        'easy_mongo_fixture:save'
    ]);
    grunt.registerTask('compile', [
        'toffee'
    ]);
    grunt.registerTask('addon', [
        'mkdir:build',
        'symlink:build',
        'execute:clean_addon',
        'mkdir:build',
        'symlink:build',
        'execute:configure_addon',
        'execute:build_addon'
    ]);
    grunt.registerTask('lint', [
        'jshint:all'
    ]);
    grunt.registerTask('test', [
        'jasmine_node:test',
        'mochaTest',
        'env:lib',
        'env:debug',
        'cucumberjs:features'
    ]);
    grunt.registerTask('doc', [
        'jsduck'
    ]);
    grunt.registerTask('default', [
        'compile',
        'addon',
        'lint',
        'test'
    ]);
};
