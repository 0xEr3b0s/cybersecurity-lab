#[derive(Debug)]
pub enum VaccineError {
    Usage(String),
    Http(String),
    Io(String),
    Parse(String),
}

use std::fmt;

impl fmt::Display for VaccineError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            VaccineError::Usage(m) => write!(f, "usage: {m}"),
            VaccineError::Http(m) => write!(f, "http: {m}"),
            VaccineError::Io(m) => write!(f, "io: {m}"),
            VaccineError::Parse(m) => write!(f, "parse: {m}"),
        }
    }
}
