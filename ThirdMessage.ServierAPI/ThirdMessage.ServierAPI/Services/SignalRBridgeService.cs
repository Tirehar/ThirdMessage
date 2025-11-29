using System.Diagnostics;

namespace ThirdMessage.ServierAPI.Services;

public class SignalRBridgeService : IHostedService, IDisposable
{
    private Process? _process;
    private readonly string _jarPath;
    private readonly string _javaExe;

    public SignalRBridgeService()
    {
        _javaExe = "java";
        _jarPath = Path.Combine(AppContext.BaseDirectory, "Plugins", "ThirdMessage.APIBridge-1.0.jar");
    }

    public Task StartAsync(CancellationToken cancellationToken)
    {
        try
        {
            if (!File.Exists(_jarPath))
            {
                return Task.CompletedTask;
            }

            var psi = new ProcessStartInfo
            {
                FileName = _javaExe,
                Arguments = $"-jar \"{_jarPath}\"",
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                CreateNoWindow = true
            };

            _process = new Process { StartInfo = psi, EnableRaisingEvents = true };
            _process.OutputDataReceived += (s, e) =>
            {
                Console.WriteLine("BridgeService:" + e.Data);
            };
            _process.ErrorDataReceived += (s, e) =>
            {
                Console.WriteLine("BridgeService:" + e.Data);
            };
            _process.Exited += (s, e) =>
            {
                //_logger.LogWarning("JAR 进程已退出，退出码 {Code}", _process?.ExitCode);
            };

            //_logger.LogInformation("启动 JAR: {Cmd} {Args}", psi.FileName, psi.Arguments);
            _process.Start();
            _process.BeginOutputReadLine();
            _process.BeginErrorReadLine();
        }
        catch (Exception ex)
        {
            //_logger.LogError(ex, "启动 JAR 时发生异常");
        }

        return Task.CompletedTask;
    }

    public Task StopAsync(CancellationToken cancellationToken)
    {
        Console.WriteLine("尝试停止");
        try
        {
            if (_process != null && !_process.HasExited)
            {
                Console.WriteLine("停止 JAR 进程 (pid={0})", _process.Id);
                _process.Kill(entireProcessTree: true);
                _process.WaitForExit(5000);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine("停止 JAR 时发生异常:" + ex.Message);
        }
        finally
        {
            _process?.Dispose();
            _process = null;
        }

        return Task.CompletedTask;
    }

    public void Dispose()
    {
        _process?.Dispose();
        _process = null;
    }
}
