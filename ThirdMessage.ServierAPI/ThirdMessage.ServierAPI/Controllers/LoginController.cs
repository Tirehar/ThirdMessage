using Microsoft.AspNetCore.Mvc;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.LoginModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class LoginController : ControllerBase
{
    [HttpPost]
    public ReplyModel<LoginReplyModel> Login([FromBody] LoginModel model)
    {
        return new ReplyModel<LoginReplyModel>
        {
            Code = 0,
            Message = "Login successful",
            Model = new LoginReplyModel
            {
                IsSuccess = true,
                Uid = 00001
            }
        };
    }

    [HttpPost]
    public ReplyModel<LoginReplyModel> Register([FromBody] LoginModel model)
    {
        return new ReplyModel<LoginReplyModel>
        {
            Code = 0,
            Message = "Registration successful",
            Model = new LoginReplyModel
            {
                IsSuccess = true,
                Uid = 00001
            }
        };
    }
}
