pub enum HttpMethod {
    Get,
    Post,
}

pub struct Config {
    pub(crate) url: String,
    pub(crate) method: HttpMethod,
    pub(crate) output: Option<String>,
}
