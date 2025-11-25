using Microsoft.EntityFrameworkCore;
using ThirdMessage.ServierAPI.Models;

namespace ThirdMessage.ServierAPI.Database;

public class ApplicationDbContext : DbContext
{
    public DbSet<UserModel> Users { get; set; }
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        var conn = "Server=(localdb)\\mssqllocaldb;Database=ThirdMessageDatabase;Trusted_Connection=True;";
        optionsBuilder.UseSqlServer(conn);
       // optionsBuilder.LogTo(Console.WriteLine);
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.ApplyConfigurationsFromAssembly(typeof(ApplicationDbContext).Assembly);
    }
}
