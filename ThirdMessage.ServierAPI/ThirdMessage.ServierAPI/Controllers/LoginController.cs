using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class LoginController : ControllerBase
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;

    public LoginController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager)
    {
        this.database = dbContext;
        this.userManager = userManager;
    }

    [HttpPost]
    public async Task<ReplyModel<LoginReplyModel>> Login([FromBody] LoginModel model)
    {
        Console.WriteLine("收到登录请求:账户" + model.Account);
        var user = await userManager.FindByNameAsync(model.Account);

        if (user == null)
        {
            //若不存在则自动注册
            Console.WriteLine("用户不存在，自动注册");
            user = await CreateUser(model);
        }
        else
        {
            //判断密码是否正确
            if (!await userManager.CheckPasswordAsync(user, model.Password))
            {
                return new ReplyModel<LoginReplyModel>
                {
                    Code = 1,
                    Message = "Incorrect password",
                    Model = new LoginReplyModel
                    {
                        IsSuccess = false,
                        Uid = "null"
                    }
                };
            }
        }

        var identity = new ClaimsIdentity(IdentityConstants.ApplicationScheme);
        identity.AddClaim(new Claim(ClaimTypes.Name, user.UserName!));
        identity.AddClaim(new Claim(ClaimTypes.NameIdentifier, user.Id));

        await HttpContext.SignInAsync(IdentityConstants.ApplicationScheme, new(identity));
        return new ReplyModel<LoginReplyModel>
        {
            Code = 0,
            Message = "Login successful",
            Model = new LoginReplyModel
            {
                IsSuccess = true,
                Uid = user.Id
            }
        };
    }

    [HttpPost]
    public async Task<ReplyModel<LoginReplyModel>> Register([FromBody] LoginModel model)
    {
        var user = await CreateUser(model);

        return new ReplyModel<LoginReplyModel>
        {
            Code = 0,
            Message = "Registration successful",
            Model = new LoginReplyModel
            {
                IsSuccess = true,
                Uid = user.Id
            }
        };
    }

    private async Task<UserEntity> CreateUser(LoginModel model)
    {
        //var messages = new List<MessageEntity>()
        //{
        //    new MessageEntity
        //    {
        //        Content = "Hello, I am A",
        //        Timestamp = DateTime.UtcNow,
        //        FromUserId = "07152545-f973-47d0-a6f9-4f94ba5580f5",
        //        ToUserId = "4fa0850b-cf18-4e3d-bd5a-47330900d621"
        //    },
        //    new MessageEntity
        //    {
        //        Content = "Hello, I am B",
        //        Timestamp = DateTime.UtcNow.AddSeconds(5),
        //        FromUserId = "07152545-f973-47d0-a6f9-4f94ba5580f5",
        //        ToUserId = "07152545-f973-47d0-a6f9-4f94ba5580f5"
        //    }
        //};

        //var friends = new List<FriendEntity>
        //    {
        //        new FriendEntity { Uid = "07152545-f973-47d0-a6f9-4f94ba5580f5",UserName = "System", Messages=messages },
        //        new FriendEntity { Uid = "4fa0850b-cf18-4e3d-bd5a-47330900d621", UserName = "TestUser", Messages=messages }
        //    };
        var user = new UserEntity() { UserName = model.Account, Friends = [] };
        var result = await userManager.CreateAsync(user, model.Password);
        if (!result.Succeeded)
        {
            foreach (var error in result.Errors)
            {
                Console.WriteLine(error.Description);
            }
        }
        return user;
    }
}
