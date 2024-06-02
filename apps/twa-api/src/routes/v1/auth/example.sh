curl  -X POST 'https://localhost:3010/v1/auth' \
     --data-raw '{"webAppData":{"query_id":null,"user":{"id":626801647,"is_bot":null,"first_name":"Roman","last_name":"Dubinskiy","username":"rvdubinskiy","language_code":"ru","allows_write_to_pm":true,"photo_url":"https://t.me/i/userpic/320/Hr0GwH0rgvZZd1Z-ozXCzztfZjEebJUnQNcqcpwyzE4.svg","added_to_attachment_menu":true},"receiver":null,"start_param":null,"auth_date":1716021867,"hash":"dc6d54b78389581095903e1be283693fca39b21ac5652e7a85913a309208eb4d","country_code_by_ip":"NL"}}' \
     -H 'Content-Type: application/json'

curl  -X POST 'https://localhost:3010/v1/auth' \
     --data-raw '{"webAppData":{"query_id":null,"user":{"id":626801647,"is_bot":null,"first_name":"Roman","last_name":"Dubinskiy","username":"rvdubinskiy","language_code":"ru","allows_write_to_pm":true,"photo_url":"https://t.me/i/userpic/320/Hr0GwH0rgvZZd1Z-ozXCzztfZjEebJUnQNcqcpwyzE4.svg","added_to_attachment_menu":true},"receiver":null,"start_param":null,"auth_date":1716021867,"hash":"dc6d54b78389581095903e1be283693fca39b21ac5652e7a85913a309208eb4d","country_code_by_ip":"NL"}}' \
     -H 'Content-Type: application/json'\
     -H 'Authorization: B'
