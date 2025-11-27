namespace ThirdMessage.ServierAPI.Helper;

public static class TimeHelper
{
    /// <summary>
    /// 将 DateTime 转为 Unix 时间戳（秒)
    /// </summary>
    public static long ToUnixSeconds(DateTime dateTime)
    {
        // 推荐：使用 DateTimeOffset 的内置方法，兼顾 DateTime.Kind
        return new DateTimeOffset(dateTime.ToUniversalTime()).ToUnixTimeSeconds();
    }

    /// <summary>
    /// 从 Unix 时间戳（秒）还原为本地 DateTime
    /// </summary>
    public static DateTime FromUnixSeconds(long seconds)
    {
        return DateTime.UnixEpoch.AddSeconds(seconds).ToLocalTime();
    }
}
