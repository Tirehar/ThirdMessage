using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using ThirdMessage.ServierAPI.Database.Entitys;

namespace ThirdMessage.ServierAPI.Database;

public class ApplicationDbContext : IdentityDbContext<UserEntity>
{
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        var conn = "Server=(localdb)\\mssqllocaldb;Database=ThirdMessageDatabase;Trusted_Connection=True;";
        optionsBuilder.UseSqlServer(conn);
       // optionsBuilder.LogTo(Console.WriteLine);
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);
        modelBuilder.ApplyConfigurationsFromAssembly(typeof(ApplicationDbContext).Assembly);
    }
}
