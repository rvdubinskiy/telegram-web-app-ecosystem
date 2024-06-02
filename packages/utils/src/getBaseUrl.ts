type Service = 'client' | 'api' | 'bot' | 'admin';

const serviceDictionary = (service: Service) => {
  switch (service) {
    case 'client':
      return process.env.TWA_CLIENT_BASTURL ?? 'http://localhost:3000';
    case 'api':
      return process.env.TWA_API_BASTURL ?? 'http://localhost:3010';
    case 'bot':
      return process.env.TWA_BOT_BASTURL ?? 'http://localhost:3020';
    case 'admin':
      return process.env.TWA_ADMIN_BASTURL ?? 'http://localhost:3030';
  }
};

export function getBaseUrl(service: Service, path = '') {
  const baseApiUrl = serviceDictionary(service) ?? '';
  return `${baseApiUrl}${path}`;
}
