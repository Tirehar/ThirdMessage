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
    private readonly ILogger<LoginController> logger;

    public LoginController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager, ILogger<LoginController> logger)
    {
        this.database = dbContext;
        this.userManager = userManager;
        this.logger = logger;
    }

    [HttpPost]
    public async Task<ReplyModel<LoginReplyModel>> Login([FromBody] LoginModel model)
    {
        logger.LogInformation("Login attempt for account: {Account}", model.Account);
        var user = await userManager.FindByNameAsync(model.Account);

        if (user == null)
        {
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
        logger.LogInformation("Registration attempt for account: {Account}", model.Account);
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
        logger.LogInformation("Creating user account: {Account}", model.Account);
        var user = new UserEntity() { UserName = model.Account, Friends = [] };
        var result = await userManager.CreateAsync(user, model.Password);
        if (!result.Succeeded)
        {
            foreach (var error in result.Errors)
            {
                logger.LogError(error.Description);
            }
        }
        return user;
    }
}
