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
                "cpp/addon.cpp",
                "cpp/addon.cpp"
            ],
            "include_dirs" : [
                "<!(node -e \"require('nan')\")",
                "../../../sandbox.cpp/src/main/cpp",
            ]
        }
    ],
}