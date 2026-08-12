pub enum HttpMethod {
    Get,
    Post,
}

pub struct Config {
    url: String,
    method: HttpMethod,
    output: Option<String>,
}
