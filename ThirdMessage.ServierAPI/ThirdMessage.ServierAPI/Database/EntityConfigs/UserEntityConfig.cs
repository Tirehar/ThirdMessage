using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using ThirdMessage.ServierAPI.Models;

namespace ThirdMessage.ServierAPI.Database.EntityConfigs;

public class UserEntityConfig : IEntityTypeConfiguration<UserModel>
{
    public void Configure(EntityTypeBuilder<UserModel> builder)
    {
        builder.ToTable("Users");
        builder.HasKey(e => e.Uid);
        builder.Property(e => e.Uid).HasMaxLength(5).IsRequired();
        builder.Property(e => e.UserName).HasMaxLength(50).IsRequired();
        builder.Property(e => e.Password).HasMaxLength(100).IsRequired();
    }
}
