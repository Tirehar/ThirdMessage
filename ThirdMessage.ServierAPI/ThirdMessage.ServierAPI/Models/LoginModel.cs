using Microsoft.AspNetCore.Mvc;
using System.ComponentModel.DataAnnotations;
using System.Globalization;
using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models;

public class LoginModel
{
    [Required]
    public string Account { get; set; }

    [Required]
    [DataType(DataType.Password)]
    public string Password { get; set; }
}
