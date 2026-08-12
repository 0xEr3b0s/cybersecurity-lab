use crate::cli::config::{Config, HttpMethod};
use crate::error::VaccineError;

pub fn parse(args: Vec<String>) -> Result<Config, VaccineError> {
    let mut method: HttpMethod = HttpMethod::Get;
    let mut output: Option<String> = None;
    let mut url: Option<String> = None;

    let mut i: usize = 1;
    while i < args.len() {
        let token: &str = &args[1];

        if token.eq("-h") || token.eq("--help") {
            return Err(VaccineError::Usage("error".to_string()));
        } else if token.eq("-X") {
            let next: Option<&str> = args.get(i + 1).map(String::as_str);
        }
    }
    Ok(())
}
