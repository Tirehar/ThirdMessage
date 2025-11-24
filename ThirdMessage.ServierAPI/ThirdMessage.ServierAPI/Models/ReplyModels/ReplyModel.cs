using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models.ReplyModels;

public class ReplyModel<T> where T : class
{
    public T Model{ get; set; }

    public string Message { get; set; }

    public int Code { get; set;}
}
