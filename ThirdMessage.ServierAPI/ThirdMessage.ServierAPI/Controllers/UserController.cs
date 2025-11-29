using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class UserController
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;
    public UserController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager)
    {
        this.userManager = userManager;
        this.database = dbContext;
    }

    [HttpGet]
    [Authorize]
    public async Task<ReplyModel<string>> GetUserID(string userName)
    {
        var user = await userManager.FindByNameAsync(userName);
        if (user != null)
        {
            return new()
            {
                Code = 0,
                Message = "Success",
                Model = user.Id
            };
        }

        return new()
        {
            Code = -1,
            Message = "User not found",
            Model = null
        };
    }
}
