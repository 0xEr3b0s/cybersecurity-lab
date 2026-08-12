use std::env;
use std::process;

fn error(msg: String, code: i32) {
    eprintln!("[ERROR] {msg}", msg=msg);
    process::exit(code);
}

fn check_args() -> Vec<String> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        error("Not enought arguments".to_owned(), 1);
    }
    args
}

fn main() {
    println!("Hello, world!");
    let args = check_args();
    println!("Passed args check");
    print!("{:?}", args);
}
