using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class LoginController : ControllerBase
{
    private readonly ApplicationDbContext database;

    public LoginController(ApplicationDbContext dbContext)
    {
        this.database = dbContext;
        
    }

    [HttpPost]
    public async Task<ReplyModel<LoginReplyModel>> Login([FromBody] LoginModel model)
    {
        Console.WriteLine("收到登录请求:账户" + model.Account );
        var keymodels = database.Users.FirstOrDefault(m => m.UserName == model.Account);
        if (keymodels == null)
        {
            //若不存在则自动注册
            database.Users.Add(new() { UserName = model.Account, Password = model.Password});
            await database.SaveChangesAsync();
        }
        else
        {
            //判断密码是否正确
            if(keymodels.Password != model.Password)
            {
                return new ReplyModel<LoginReplyModel>
                {
                    Code = 1,
                    Message = "Incorrect password",
                    Model = new LoginReplyModel
                    {
                        IsSuccess = false,
                        Uid = -1
                    }
                };
            }
        }
        return new ReplyModel<LoginReplyModel>
        {
            Code = 0,
            Message = "Login successful",
            Model = new LoginReplyModel
            {
                IsSuccess = true,
                Uid = database.Users.FirstOrDefault(m => m.UserName == model.Account)!.Uid
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
