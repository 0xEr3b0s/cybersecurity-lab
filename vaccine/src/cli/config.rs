pub enum HttpMethod {
    Get,
    Post,
}

pub struct Config {
    url: String,
    method: HttpMethod,
    pub(crate) output: Option<String>,
}
