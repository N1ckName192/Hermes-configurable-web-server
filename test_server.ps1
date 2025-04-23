Write-Host "=== Testing HTTP Server ==="

# 1. Проверка основного маршрута
$response = Invoke-WebRequest -Uri "http://localhost:8080/" -Method Get
if (-not $response.Content.Contains("Hermes HTTP Server")) {
    Write-Host "FAIL: Main page test failed"
    Read-Host "Press Enter to exit"
    exit 1
}

# 2. Проверка JSON-маршрута
$response = Invoke-WebRequest -Uri "http://localhost:8080/test" -Method Get
if (-not $response.Content.Contains('"status":"success"')) {
    Write-Host "FAIL: JSON route test failed"
    Read-Host "Press Enter to exit"
    exit 1
}

# 3. Проверка прокси (порт 9090)
$response = Invoke-WebRequest -Uri "http://localhost:9090/work" -Method Get
if (-not $response.Content.Contains("The server is working correctly!")) {
    Write-Host "FAIL: Proxy test failed"
    Read-Host "Press Enter to exit"
    exit 1
}

# 4. Проверка TCP соединения
$tcpClient = New-Object System.Net.Sockets.TcpClient
try {
    $tcpClient.Connect("localhost", 8080)
    $stream = $tcpClient.GetStream()
    $writer = New-Object System.IO.StreamWriter($stream)
    $reader = New-Object System.IO.StreamReader($stream)
    
    $writer.WriteLine("GET / HTTP/1.1")
    $writer.WriteLine("Host: localhost")
    $writer.WriteLine("")
    $writer.Flush()
    
    $firstLine = $reader.ReadLine()
    if (-not $firstLine.Contains("200 OK")) {
        Write-Host "FAIL: TCP test failed"
        Read-Host "Press Enter to exit"
        exit 1
    }
}
finally {
    $tcpClient.Close()
}

Write-Host "=== All tests passed successfully! ==="
Read-Host "Press Enter to exit"
exit 0
