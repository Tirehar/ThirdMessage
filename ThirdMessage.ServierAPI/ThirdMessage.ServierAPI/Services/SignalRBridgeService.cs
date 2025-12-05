using System.Diagnostics;

namespace ThirdMessage.ServierAPI.Services;

public class SignalRBridgeService : IHostedService, IDisposable
{
    private Process? _process;
    private readonly string _jarPath;
    private readonly string _javaExe;
    private readonly ILogger<SignalRBridgeService> logger;

    public SignalRBridgeService(ILogger<SignalRBridgeService> logger)
    {
        _javaExe = "java";
        _jarPath = Path.Combine(AppContext.BaseDirectory, "Plugins", "ThirdMessage.APIBridge-1.0.jar");
        this.logger = logger;
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
                logger.LogInformation(e.Data);
            };
            _process.ErrorDataReceived += (s, e) =>
            {
                logger.LogError(e.Data);
            };

            logger.LogInformation("Starting: {Cmd} {Args}", psi.FileName, psi.Arguments);
            _process.Start();
            _process.BeginOutputReadLine();
            _process.BeginErrorReadLine();
        }
        catch (Exception ex)
        {
            logger.LogError(ex.Message);
        }

        return Task.CompletedTask;
    }

    public Task StopAsync(CancellationToken cancellationToken)
    {
        try
        {
            if (_process != null && !_process.HasExited)
            {
                logger.LogWarning("Stopped (pid={0})", _process.Id);
                _process.Kill(entireProcessTree: true);
                _process.WaitForExit(5000);
            }
        }
        catch (Exception ex)
        {
            logger.LogError("Stop Error:" + ex.Message);
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
