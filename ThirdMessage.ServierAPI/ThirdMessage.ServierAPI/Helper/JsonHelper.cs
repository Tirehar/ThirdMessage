using System.Text.Json;

namespace ThirdMessage.ServierAPI.Helper;

public static class JsonHelper
{
    /// <summary>
    /// 将对象序列化为 JSON 字符串。
    /// </summary>
    /// <typeparam name="T">要序列化的对象类型。</typeparam>
    /// <param name="obj">要序列化的对象。</param>
    /// <returns>表示对象的 JSON 字符串。</returns>
    public static string ToJson<T>(T obj)
    {
        return JsonSerializer.Serialize(obj);
    }

    /// <summary>
    /// 将 JSON 字符串反序列化为指定类型的对象。
    /// </summary>
    /// <typeparam name="T">要反序列化为的对象类型。</typeparam>
    /// <param name="json">要反序列化的 JSON 字符串。</param>
    /// <returns>从 JSON 字符串反序列化得到的对象。</returns>
    public static T ToObject<T>(string json)
    {
        return JsonSerializer.Deserialize<T>(json);
    }
}
