use std::env;
use std::fs;
use std::path::{Path, PathBuf};
use std::process;

struct Config {
    query: String,
    path: PathBuf,
    ignore_case: bool,
    extension: Option<String>,
}

fn print_help() {
    println!("textgrep - search text recursively inside files");
    println!();
    println!("Usage:");
    println!("  textgrep <query> <path>");
    println!("  textgrep <query> <path> --ignore-case");
    println!("  textgrep <query> <path> --ext <extension>");
    println!();
    println!("Options:");
    println!("  -i, --ignore-case    ignore case when searching");
    println!("  --ext <extension>    search only files with this extension");
    println!("  -h, --help           show this help message");
}

fn parse_args() -> Config {
    let args: Vec<String> = env::args().skip(1).collect();

    if args.is_empty()
        || args.iter().any(|arg| arg == "--help" || arg == "-h")
    {
        print_help();
        process::exit(0);
    }

    if args.len() < 2 {
        eprintln!("Usage: textgrep <query> <path> [options]");
        process::exit(1);
    }

    let query = args[0].clone();
    let path = PathBuf::from(&args[1]);

    let mut ignore_case = false;
    let mut extension = None;

    let mut i = 2;

    while i < args.len() {
        match args[i].as_str() {
            "-i" | "--ignore-case" => {
                ignore_case = true;
            }

            "--ext" => {
                if i + 1 >= args.len() {
                    eprintln!("Error: --ext requires an extension");
                    process::exit(1);
                }

                extension = Some(args[i + 1].clone());
                i += 1;
            }

            option => {
                eprintln!("Error: unknown option: {option}");
                process::exit(1);
            }
        }

        i += 1;
    }

    Config {
        query,
        path,
        ignore_case,
        extension,
    }
}

fn search_file(
    file_path: &Path,
    query: &str,
    ignore_case: bool,
    matches: &mut usize,
) -> bool {
    let Ok(text) = fs::read_to_string(file_path) else {
        return false;
    };

    let mut found = false;

    for (line_number, line) in text.lines().enumerate() {
        let is_match = if ignore_case {
            line.to_lowercase().contains(query)
        } else {
            line.contains(query)
        };

        if is_match {
            println!(
                "{}:{}: {}",
                file_path.display(),
                line_number + 1,
                line
            );

            *matches += 1;
            found = true;
        }
    }

    found
}

fn search_directory(
    dir_path: &Path,
    query: &str,
    ignore_case: bool,
    extension: Option<&str>,
    matches: &mut usize,
    files_with_matches: &mut usize,
) {
    let Ok(entries) = fs::read_dir(dir_path) else {
        return;
    };

    for entry in entries.flatten() {
        let path = entry.path();

        if path.is_dir() {
            search_directory(
                &path,
                query,
                ignore_case,
                extension,
                matches,
                files_with_matches,
            );

            continue;
        }

        if !path.is_file() {
            continue;
        }

        if let Some(ext) = extension {
            if path.extension().and_then(|e| e.to_str()) != Some(ext) {
                continue;
            }
        }

        if search_file(
            &path,
            query,
            ignore_case,
            matches,
        ) {
            *files_with_matches += 1;
        }
    }
}

fn main() {
    let config = parse_args();

    let query = if config.ignore_case {
        config.query.to_lowercase()
    } else {
        config.query.clone()
    };

    let mut matches = 0;
    let mut files_with_matches = 0;

    search_directory(
        &config.path,
        &query,
        config.ignore_case,
        config.extension.as_deref(),
        &mut matches,
        &mut files_with_matches,
    );

    println!();

    println!(
        "{} matches in {} files",
        matches,
        files_with_matches
    );
}