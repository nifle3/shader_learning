{ pkgs, lib, config, inputs, ... }:
{
  packages = with pkgs; [ 
    git 
    ninja
    wayland
    wayland-scanner
    libffi
    libGL
    libxkbcommon
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
  ];

  env.LD_LIBRARY_PATH = [ "${config.env.DEVENV_PROFILE}/lib" ];

  languages.cplusplus = {
    enable = true;
    lsp.enable = true;
  };

  scripts.hello.exec = ''
    echo hello from $GREET
  '';

  enterShell = ''
    hello         # Run scripts directly
    git --version # Use packages
  '';

  tasks = {
    "debug:setup" = {
      exec = "cmake --preset debug";
      execIfModified = [
        "**/CMakeLists.txt"
        "CMakePresets.json"
      ];
    };
    "debug:build" = {
      exec = "cmake --build --preset debug";
      execIfModified = [
        "**/*.cc"
        "**/*.hpp"
        "shaders/*"
      ];
      after = [ "debug:setup" ];
    };
    "debug:run" = {
      exec = "./build/debug/shaders_learning";
      after = [ "debug:build" ];
    };
  };
}
