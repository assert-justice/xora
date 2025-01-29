import sd_utils

def main():
    with sd_utils.Cli() as cli:
        cli.cd('build')
        cli.run(['ninja'])
        cli.reset()
        cli.copy('./build/xora.exe', './dist')
        cli.cd('dist')
        cli.run(['./xora.exe'])
    # cd into build
    # run ninja
    # copy xora.exe (or just xora) to dist
    pass

if __name__ == "__main__":
    main()