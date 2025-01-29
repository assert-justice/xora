import sd_utils
import platform

def main():
    exe_ext = '.exe' if platform.system() == 'Windows' else ''
    with sd_utils.Cli() as cli:
        if not cli.is_dir('build'):
            cli.mkdir('build')
        cli.cd('build')
        if not cli.is_file('build.ninja'):
            cli.run('cmake .. -G Ninja')
        cli.run(['ninja'])
        cli.reset()
        cli.copy(f'./build/xora{exe_ext}', './dist')
        cli.cd('dist')
        cli.run([f'./xora{exe_ext}'])

if __name__ == "__main__":
    main()