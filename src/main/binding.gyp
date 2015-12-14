{
    "target_defaults": {
        "cflags_cc": [
            "-std=gnu++11",
            "-fexceptions",
            "-frtti",
            "-g",
            "-O0",
            "-fPIC"
        ],
        "cflags_cc!": [
            "-fno-rtti",
            "-fno-exceptions"
        ]
    },
    "targets": [
        {
            "target_dir": "../../target/build",
            "target_name": "sandbox_cpp",
            "sources": [
                "cpp/ontology/topic.cpp",
                "cpp/addon.cpp"
            ],
            "include_dirs" : [
                "<!(node -e \"require('nan')\")",
                "cpp",
                "../../../sandbox.cpp/src/include/cpp",
            ]
        }
    ],
}