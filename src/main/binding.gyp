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
    "conditions": [
        ["OS=='linux'", {
            "targets": [
                {
                    "target_name": "sandbox_cpp",
                    "sources": [
                        "cpp/ontology/topic.cpp",
                        "cpp/taxonomy/genus.cpp",
                        "cpp/taxonomy/species.cpp",
                        "cpp/addon.cpp"
                    ],
                    "include_dirs": [
                        "<!(node -e \"require('nan')\")",
                        "cpp",
                        "/com.u14n/sandbox/sandbox.cpp/src/include/cpp",
                    ],
                    "link_settings": {
                        "libraries": [
                            "-L /com.u14n/sandbox/sandbox.cpp/build",
                            "-l sandbox"
                        ]
                    }
                }
            ]
        }]
    ]
}