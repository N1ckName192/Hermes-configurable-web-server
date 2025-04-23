# Colors for output
$Green = [ConsoleColor]::Green
$Red = [ConsoleColor]::Red
$Yellow = [ConsoleColor]::Yellow
$Cyan = [ConsoleColor]::Cyan
$White = [ConsoleColor]::White

function Write-ColorOutput($ForegroundColor) {
    $fc = $host.UI.RawUI.ForegroundColor
    $host.UI.RawUI.ForegroundColor = $ForegroundColor
    if ($args) {
        Write-Output $args
    }
    $host.UI.RawUI.ForegroundColor = $fc
}

function Test-Routing {
    param (
        [string]$Url,
        [string]$ExpectedContent,
        [string]$TestName
    )
    
    Write-ColorOutput $Cyan "Testing routing: $TestName..."
    Write-ColorOutput $White "  URL: $Url"
    
    try {
        $response = Invoke-WebRequest -Uri $Url -Method Get
        if ($response.Content.Contains($ExpectedContent)) {
            Write-ColorOutput $Green "  ✓ PASS: Route handled correctly"
            Write-ColorOutput $White "  Response time: $($response.TimeMs)ms"
            return $true
        } else {
            Write-ColorOutput $Red "  ✗ FAIL: Route not handled correctly"
            Write-ColorOutput $Yellow "  Expected: $ExpectedContent"
            Write-ColorOutput $Yellow "  Got: $($response.Content)"
            return $false
        }
    } catch {
        Write-ColorOutput $Red "  ✗ FAIL: $($_.Exception.Message)"
        return $false
    }
}

function Test-Proxy {
    param (
        [string]$ProxyUrl,
        [string]$DirectUrl,
        [string]$TestName
    )
    
    Write-ColorOutput $Cyan "Testing proxy: $TestName..."
    Write-ColorOutput $White "  Proxy URL: $ProxyUrl"
    Write-ColorOutput $White "  Direct URL: $DirectUrl"
    
    try {
        $proxyResponse = Invoke-WebRequest -Uri $ProxyUrl -Method Get
        $directResponse = Invoke-WebRequest -Uri $DirectUrl -Method Get
        
        if ($proxyResponse.Content -eq $directResponse.Content) {
            Write-ColorOutput $Green "  ✓ PASS: Proxy response matches direct response"
            Write-ColorOutput $White "  Proxy time: $($proxyResponse.TimeMs)ms"
            Write-ColorOutput $White "  Direct time: $($directResponse.TimeMs)ms"
            return $true
        } else {
            Write-ColorOutput $Red "  ✗ FAIL: Proxy response differs from direct response"
            Write-ColorOutput $Yellow "  Proxy content length: $($proxyResponse.Content.Length)"
            Write-ColorOutput $Yellow "  Direct content length: $($directResponse.Content.Length)"
            return $false
        }
    } catch {
        Write-ColorOutput $Red "  ✗ FAIL: $($_.Exception.Message)"
        return $false
    }
}

function Test-TcpConnection {
    param (
        [string]$Server = "localhost",
        [int]$Port = 7070
    )

    Write-ColorOutput $Cyan "Testing TCP connection to $Server`:$Port..."

    try {
        $tcpClient = New-Object System.Net.Sockets.TcpClient
        $tcpClient.Connect($Server, $Port)
        $stream = $tcpClient.GetStream()

        # Отправляем PING
        $bytes = [System.Text.Encoding]::ASCII.GetBytes("PING")
        $stream.Write($bytes, 0, $bytes.Length)
        $stream.Flush()

        # Читаем ответ
        $response = New-Object byte[] 4
        $bytesRead = $stream.Read($response, 0, $response.Length)
        $text = [System.Text.Encoding]::ASCII.GetString($response, 0, $bytesRead)

        $tcpClient.Close()

        if ($text -eq "PONG") {
            Write-ColorOutput $Green "✓ TCP test passed - received PONG response"
            return $true
        } else {
            Write-ColorOutput $Red "✗ TCP test failed - unexpected response: $text"
            return $false
        }
    } catch {
        Write-ColorOutput $Red "✗ TCP test failed - $($_.Exception.Message)"
        return $false
    }
}

# Main test execution
Write-ColorOutput $White "=== Hermes Server Test Suite ==="
Write-ColorOutput $White "Starting tests at $(Get-Date -Format 'HH:mm:ss')"
Write-ColorOutput $White ""

$allTestsPassed = $true

# Routing Tests
Write-ColorOutput $White "=== Routing Tests ==="
$allTestsPassed = $allTestsPassed -and (Test-Routing "http://localhost:8080/" "Hermes HTTP Server" "Root Path")
$allTestsPassed = $allTestsPassed -and (Test-Routing "http://localhost:8080/test" '"status":"success"' "JSON API")
$allTestsPassed = $allTestsPassed -and (Test-Routing "http://localhost:8080/work" "The server is working correctly!" "Work Endpoint")
$allTestsPassed = $allTestsPassed -and (Test-Routing "http://localhost:8080/static/index.html" "<html" "Static Files")

# Proxy Tests
Write-ColorOutput $White "`n=== Proxy Tests ==="
$allTestsPassed = $allTestsPassed -and (Test-Proxy "http://localhost:9090/" "http://localhost:8080/" "Root Path")
$allTestsPassed = $allTestsPassed -and (Test-Proxy "http://localhost:9090/test" "http://localhost:8080/test" "JSON API")
$allTestsPassed = $allTestsPassed -and (Test-Proxy "http://localhost:9090/work" "http://localhost:8080/work" "Work Endpoint")
$allTestsPassed = $allTestsPassed -and (Test-Proxy "http://localhost:9090/static/index.html" "http://localhost:8080/static/index.html" "Static Files")

# TCP Tests
Write-ColorOutput $White "`n=== TCP Tests ==="
$tcpTest = Test-TcpConnection
$allTestsPassed = $allTestsPassed -and $tcpTest

# Summary
Write-ColorOutput $White "`n=== Test Summary ==="
if ($allTestsPassed) {
    Write-ColorOutput $Green "✓ All tests passed successfully!"
} else {
    Write-ColorOutput $Red "✗ Some tests failed!"
}

Write-ColorOutput $White "`nTest execution completed at $(Get-Date -Format 'HH:mm:ss')"
Write-ColorOutput $White "Press Enter to exit..."

# Wait for Enter key
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
Start-Sleep -Seconds 1

if ($allTestsPassed) { exit 0 } else { exit 1 }
